pointOnLine(double px,double py, double ax, double ay, double bx, double by, double& tx) {
        double dx=bx-ax;
        double dy=by-ay;
        double ty=0;
        if(fabs(dx)<0.0001&&fabs(dy)<0.0001) {

            tx=px-ax;
            ty=py-ay;
        } else {
            if(fabs(dx)<0.0001) {

                if(fabs(px-ax)<0.01) {
                   tx=(py-ay)/dy;
                }
            } else {
                tx=(px-ax)/dx;
            }
            if(fabs(dy)<0.0001) {

                if(fabs(py-ay)<0.01) {
                   ty=tx;
                }
            } else {
                ty=(py-ay)/dy;
            }
        }

        if(fabs(tx-ty)<0.001 && tx>0 && tx<=1) {
            return true;
        }
        return false;
    }
