decode_block_dc_first(jpeg_decoder *pD, int component_id, int block_x, int block_y)
{
    int s, r;
    jpgd_block_t *p = pD->coeff_buf_getp(pD->m_dc_coeffs[component_id], block_x, block_y);

    if ((s = pD->huff_decode(pD->m_pHuff_tabs[pD->m_comp_dc_tab[component_id]])) != 0) {
        r = pD->get_bits_no_markers(s);
        s = JPGD_HUFF_EXTEND(r, s);
    }

    pD->m_last_dc_val[component_id] = (s += pD->m_last_dc_val[component_id]);

    p[0] = static_cast<jpgd_block_t>(s << pD->m_successive_low);
}
