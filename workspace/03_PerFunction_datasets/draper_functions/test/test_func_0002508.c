rtl2832_sdr_free_stream_bufs(struct rtl2832_sdr_dev *dev)
{
	struct platform_device *pdev = dev->pdev;

	if (test_bit(URB_BUF, &dev->flags)) {
		while (dev->buf_num) {
			dev->buf_num--;
			dev_dbg(&pdev->dev, "free buf=%d\n", dev->buf_num);
			usb_free_coherent(dev->udev, dev->buf_size,
					  dev->buf_list[dev->buf_num],
					  dev->dma_addr[dev->buf_num]);
		}
	}
	clear_bit(URB_BUF, &dev->flags);

	return 0;
}
