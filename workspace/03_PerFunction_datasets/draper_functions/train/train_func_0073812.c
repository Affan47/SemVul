makeNiceScaleTicks(double& min, double& max, uint8_t& steps) {
    double interval = (max - min) / steps;


    if (max > (uint64_t) max) {
        max = (uint64_t) max + 1;
    }

    if (min - interval < 0)
        min = 0;
    else {
        min = (uint64_t) min;
    }


}
