persistancy(bool persist) {
        if (persist) {
            ++persistant;
        }
        else {
            --persistant;
            if (persistant <= 0) {
                persistant = 0;
                disconnect();
            }
        }
    }
