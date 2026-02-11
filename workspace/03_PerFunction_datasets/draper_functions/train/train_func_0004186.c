main(int argc, char** argv) {
    int n, m;
    double gamma;
    imageP	I1, I2, tmp_img;

    I1 = IP_readImage(argv[1]);
    I2 = NEWIMAGE;
    tmp_img = NEWIMAGE;


    m = atoi(argv[2]);
    n = pow(m, 2);


    if (n != 9) {
        if (not(is_pow_of_2(n))) {
            cerr << n << " is not a power of 2. Exiting." << endl;
            exit(1);
        }
    }
    gamma = atof(argv[3]);


    ordered_dither(I1, n, gamma, I2, tmp_img, m);
    IP_saveImage(I2, argv[4]);


    IP_freeImage(I1);
    IP_freeImage(I2);
    IP_freeImage(tmp_img);
	return 1;
}
