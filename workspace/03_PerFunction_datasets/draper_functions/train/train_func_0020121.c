AdaptiveLPPermute(jxr_image_t image, int dst[16], const int src[16])
{
    int idx;
    for (idx = 1 ; idx < 16 ; idx += 1) {

        int map = image->lopass_scanorder[idx-1];
        dst[idx] = src[map];

        if (dst[idx] == 0)
            continue;

        image->lopass_scantotals[idx-1] += 1;

        if (idx > 1 && image->lopass_scantotals[idx-1] > image->lopass_scantotals[idx-2]) {
            SWAP(image->lopass_scantotals[idx-1], image->lopass_scantotals[idx-2]);
            SWAP(image->lopass_scanorder[idx-1], image->lopass_scanorder[idx-2]);
        }
    }
}
