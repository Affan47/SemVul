setHSB(Real hue, Real saturation, Real brightness)
    {

        if (hue > 1.0f)
        {
            hue -= (int)hue;
        }
        else if (hue < 0.0f)
        {
            hue += (int)hue + 1;
        }

        saturation = std::min(saturation, (Real)1.0);
        saturation = std::max(saturation, (Real)0.0);
        brightness = std::min(brightness, (Real)1.0);
        brightness = std::max(brightness, (Real)0.0);

        if (brightness == 0.0f)
        {

            r = g = b = 0.0f;
            return;
        }

        if (saturation == 0.0f)
        {


            r = g = b = brightness;
            return;
        }


        Real hueDomain  = hue * 6.0f;
        if (hueDomain >= 6.0f)
        {

            hueDomain = 0.0f;
        }
        unsigned short domain = (unsigned short)hueDomain;
        Real f1 = brightness * (1 - saturation);
        Real f2 = brightness * (1 - saturation * (hueDomain - domain));
        Real f3 = brightness * (1 - saturation * (1 - (hueDomain - domain)));

        switch (domain)
        {
        case 0:

            r = brightness;
            g = f3;
            b = f1;
            break;
        case 1:

            r = f2;
            g = brightness;
            b = f1;
            break;
        case 2:

            r = f1;
            g = brightness;
            b = f3;
            break;
        case 3:

            r = f1;
            g = f2;
            b = brightness;
            break;
        case 4:

            r = f3;
            g = f1;
            b = brightness;
            break;
        case 5:

            r = brightness;
            g = f1;
            b = f2;
            break;
        }


    }
