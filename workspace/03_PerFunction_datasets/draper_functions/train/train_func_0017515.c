bcf_p1_set_folded(bcf_p1aux_t *p1a)
{
	if (p1a->n1 < 0) {
		p1a->is_folded = 1;
		fold_array(p1a->M, p1a->phi);
		fold_array(p1a->M, p1a->phi_indel);
	}
}
