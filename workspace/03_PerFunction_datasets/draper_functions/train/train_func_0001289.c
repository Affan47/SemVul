rle_run(float *dc, unsigned char *dc_mask, float avg, unsigned int start, unsigned int width, const float maxerror) {
    unsigned int left = start, right = start;
    float acc = dc[start];

    bool left_stuck = false, right_stuck = false;
    do {
        const float len = right - left + 1;

        if (!left_stuck && left > 0) {
            const float x0 = dc[left-1];
            const float diff = colordifference(avg, x0) * dc_masking_level/(dc_masking_level+dc_mask[left-1]);
            if (diff < maxerror) {
                acc += x0;
                left--;
            }
            else left_stuck = true;
        }
        else left_stuck = true;

        if (!right_stuck && right < width-2) {
            const float x0 = dc[right+1];
            const float diff = colordifference(avg, x0) * dc_masking_level/(dc_masking_level+dc_mask[right+1]);
            if (diff < maxerror) {
                acc += x0;
                right++;
            }
            else right_stuck = true;
        }
        else right_stuck = true;

    } while(!left_stuck || !right_stuck);

    return (lra){
        left, right, acc,
    };
}
