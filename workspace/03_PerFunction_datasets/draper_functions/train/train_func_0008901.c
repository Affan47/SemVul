ath10k_ce_revoke_recv_next(struct ath10k_ce_pipe *ce_state,
			       void **per_transfer_contextp,
			       u32 *bufferp)
{
	struct ath10k_ce_ring *dest_ring;
	unsigned int nentries_mask;
	unsigned int sw_index;
	unsigned int write_index;
	int ret;
	struct ath10k *ar;
	struct ath10k_pci *ar_pci;

	dest_ring = ce_state->dest_ring;

	if (!dest_ring)
		return -EIO;

	ar = ce_state->ar;
	ar_pci = ath10k_pci_priv(ar);

	spin_lock_bh(&ar_pci->ce_lock);

	nentries_mask = dest_ring->nentries_mask;
	sw_index = dest_ring->sw_index;
	write_index = dest_ring->write_index;
	if (write_index != sw_index) {
		struct ce_desc *base = dest_ring->base_addr_owner_space;
		struct ce_desc *desc = CE_DEST_RING_TO_DESC(base, sw_index);


		*bufferp = __le32_to_cpu(desc->addr);

		if (per_transfer_contextp)
			*per_transfer_contextp =
				dest_ring->per_transfer_context[sw_index];


		dest_ring->per_transfer_context[sw_index] = NULL;
		desc->nbytes = 0;


		sw_index = CE_RING_IDX_INCR(nentries_mask, sw_index);
		dest_ring->sw_index = sw_index;
		ret = 0;
	} else {
		ret = -EIO;
	}

	spin_unlock_bh(&ar_pci->ce_lock);

	return ret;
}
