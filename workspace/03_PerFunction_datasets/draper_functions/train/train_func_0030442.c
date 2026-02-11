fillSolidBoxSolidBoxInfo(
        const Box & box1,
        const Box & box2,
        Vector3 & a,
        Vector3 & b,
        Vector3 & D,
        double* c,
        double* ca,
        double* ad,
        double* bd) {

    a = box1.extent() * 0.5;
    b = box2.extent() * 0.5;


    D = box2.center() - box1.center();


    for (int i = 0; i < 9; i++) {
        c[i] = dot(box1.axis(i / 3), box2.axis(i % 3));
        ca[i] = fabs(c[i]);
    }


    for (int i = 0; i < 3; i++) {
        ad[i] = dot(box1.axis(i), D);
        bd[i] = dot(box2.axis(i), D);
    }
}
