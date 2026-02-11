deriveCPParameters()
{

    const double t1 = USE_T0_IN_CP_MODEL ? 0.25 : 1;
    const double t2 = 6;


    const double t3 = 10;
    const double t4 = 60;


    int i1, i2, i3, i4;


    for (i1 = 0; i1 < 60 * t1; i1++)
        if (i1 + 1 >= bests->meanMaxArray(series).size())
            return;

    for (i2 = i1; i2 + 1 <= 60 * t2; i2++)
        if (i2 + 1 >= bests->meanMaxArray(series).size())
            return;

    for (i3 = i2; i3 < 60 * t3; i3++)
        if (i3 + 1 >= bests->meanMaxArray(series).size())
            return;
    for (i4 = i3; i4 + 1 <= 60 * t4; i4++)
        if (i4 + 1 >= bests->meanMaxArray(series).size())
            break;


    if (tau == 0)
        tau = 1;


    if (cp == 0)
        cp = 300;


    t0 = 0;


    const double tau_min = 0.5;


    const double tau_delta_max = 1e-4;
    const double t0_delta_max  = 1e-4;


    double tau_prev;
    double t0_prev;


    const int max_loops = 100;


    int iteration = 0;
    do {
        if (iteration ++ > max_loops) {
            QMessageBox::warning(
                NULL, "Warning",
                QString("Maximum number of loops %d exceeded in cp model"
                        "extraction").arg(max_loops),
                QMessageBox::Ok,
                QMessageBox::NoButton);
            break;
        }


        tau_prev = tau;
        t0_prev  = t0;


        int i;
        cp = 0;
        for (i = i3; i <= i4; i++) {
            double cpn = bests->meanMaxArray(series)[i] / (1 + tau / (t0 + i / 60.0));
            if (cp < cpn)
                cp = cpn;
        }


        if (cp == 0.0)
            return;


        tau = tau_min;
        for (i = i1; i <= i2; i++) {
            double taun = (bests->meanMaxArray(series)[i] / cp - 1) * (i / 60.0 + t0) - t0;
            if (tau < taun)
                tau = taun;
        }


        #if USE_T0_IN_CP_MODEL
        t0 = tau / (bests->meanMaxArray(series)[1] / cp - 1) - 1 / 60.0;
        #endif

    } while ((fabs(tau - tau_prev) > tau_delta_max) ||
             (fabs(t0 - t0_prev) > t0_delta_max)
            );
}
