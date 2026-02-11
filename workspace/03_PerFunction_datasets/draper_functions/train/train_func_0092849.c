draw(AW_device *device, int x, int y) const {
        e4_assert(lines);
        for (int l=0; l<lines; l++) {
            int p1 = start[l];
            int p2 = end[l];
            device->line(ED4_G_CURSOR, xpos[p1]+x, ypos[p1]+y, xpos[p2]+x, ypos[p2]+y, 1, 0, 0);
        }
        device->flush();
    }
