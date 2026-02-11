_jxr_ResetTotalsAdaptiveScanHP(jxr_image_t image)
{
    int idx;
    for (idx = 0 ; idx < 15 ; idx += 1) {
        image->hipass_hor_scantotals[idx] = ScanTotals[idx];
        image->hipass_ver_scantotals[idx] = ScanTotals[idx];
    }
}
