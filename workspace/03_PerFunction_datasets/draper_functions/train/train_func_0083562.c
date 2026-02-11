e1000_alloc_rx_buffers(struct e1000_adapter *adapter,
				   struct e1000_rx_ring *rx_ring,
				   int cleaned_count)
{
	struct e1000_hw *hw = &adapter->hw;
	struct pci_dev *pdev = adapter->pdev;
	struct e1000_rx_desc *rx_desc;
	struct e1000_rx_buffer *buffer_info;
	unsigned int i;
	unsigned int bufsz = adapter->rx_buffer_len;

	i = rx_ring->next_to_use;
	buffer_info = &rx_ring->buffer_info[i];

	while (cleaned_count--) {
		void *data;

		if (buffer_info->rxbuf.data)
			goto skip;

		data = e1000_alloc_frag(adapter);
		if (!data) {

			adapter->alloc_rx_buff_failed++;
			break;
		}


		if (!e1000_check_64k_bound(adapter, data, bufsz)) {
			void *olddata = data;
			e_err(rx_err, "skb align check failed: %u bytes at "
			      "%p\n", bufsz, data);

			data = e1000_alloc_frag(adapter);

			if (!data) {
				skb_free_frag(olddata);
				adapter->alloc_rx_buff_failed++;
				break;
			}

			if (!e1000_check_64k_bound(adapter, data, bufsz)) {

				skb_free_frag(data);
				skb_free_frag(olddata);
				adapter->alloc_rx_buff_failed++;
				break;
			}


			skb_free_frag(olddata);
		}
		buffer_info->dma = dma_map_single(&pdev->dev,
						  data,
						  adapter->rx_buffer_len,
						  DMA_FROM_DEVICE);
		if (dma_mapping_error(&pdev->dev, buffer_info->dma)) {
			skb_free_frag(data);
			buffer_info->dma = 0;
			adapter->alloc_rx_buff_failed++;
			break;
		}


		if (!e1000_check_64k_bound(adapter,
					(void *)(unsigned long)buffer_info->dma,
					adapter->rx_buffer_len)) {
			e_err(rx_err, "dma align check failed: %u bytes at "
			      "%p\n", adapter->rx_buffer_len,
			      (void *)(unsigned long)buffer_info->dma);

			dma_unmap_single(&pdev->dev, buffer_info->dma,
					 adapter->rx_buffer_len,
					 DMA_FROM_DEVICE);

			skb_free_frag(data);
			buffer_info->rxbuf.data = NULL;
			buffer_info->dma = 0;

			adapter->alloc_rx_buff_failed++;
			break;
		}
		buffer_info->rxbuf.data = data;
 skip:
		rx_desc = E1000_RX_DESC(*rx_ring, i);
		rx_desc->buffer_addr = cpu_to_le64(buffer_info->dma);

		if (unlikely(++i == rx_ring->count))
			i = 0;
		buffer_info = &rx_ring->buffer_info[i];
	}

	if (likely(rx_ring->next_to_use != i)) {
		rx_ring->next_to_use = i;
		if (unlikely(i-- == 0))
			i = (rx_ring->count - 1);


		wmb();
		writel(i, hw->hw_addr + rx_ring->rdt);
	}
}
