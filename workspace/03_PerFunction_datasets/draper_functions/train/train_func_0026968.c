dt2ts (date,time)

double	date;


double	time;


{
    double tsec;

    double dh,dm,dd;
    int iy,im,id;


    if (time < 0.0)
	tsec = time * -86400.0;
    else {
	dh = (int) (time + 0.0000000001);
	dm = (int) (((time - dh) * 100.0) + 0.0000000001);
	tsec = (time * 10000.0) - (dh * 10000.0) - (dm * 100.0);
	tsec = (int) (tsec * 100000.0 + 0.0001) / 100000.0;
	tsec = tsec + (dm * 60.0) + (dh * 3600.0);
	}


    if (date >= 0.0301) {
	iy = (int) (date + 0.0000000001);
	im = (int) (((date - (double) (iy)) * 10000.0) + 0.00000001);
	id = im % 100;
	im = (im / 100) + 9;
	if (im < 12) iy = iy - 1;
	im = im % 12;
	id = id - 1;


	id = id + ((im+1+im/6+im/11)/2 * 31) + ((im-im/6-im/11)/2 * 30) +
	     (iy / 4) - (iy / 100) + (iy / 400);
	dd = (double) id + (365.0 * (double) iy) - 712163.0;
	tsec = tsec + (dd * 86400.0);
	}

    return (tsec);
}
