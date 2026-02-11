exposureTime(float shutterSpeedValue)
    {
        URational ur(1, 1);
        double tmp = std::exp(std::log(2.0) * shutterSpeedValue);
        if (tmp > 1) {
            ur.second = static_cast<long>(tmp + 0.5);
        }
        else {
            ur.first = static_cast<long>(1/tmp + 0.5);
        }
        return ur;
    }
