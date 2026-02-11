sharpen(QImage &image, double radius, double sigma)
{
    double alpha, normalize, *kernel;
    int width;
    register long i, u, v;
    QImage dest;

    if(sigma == 0.0){

        return(dest);
    }
    width = getOptimalKernelWidth(radius, sigma);
    if(image.width() < width){

        return(dest);
    }
    kernel = (double *)malloc(width*width*sizeof(double));
    if(!kernel){

        return(dest);
    }

    i = 0;
    normalize=0.0;
    for(v=(-width/2); v <= (width/2); v++){
        for(u=(-width/2); u <= (width/2); u++){
            alpha=exp(-((double) u*u+v*v)/(2.0*sigma*sigma));
            kernel[i]=alpha/(2.0*MagickPI*sigma*sigma);
            normalize+=kernel[i];
            i++;
        }
    }
    kernel[i/2]=(-2.0)*normalize;
    convolveImage(&image, &dest, width, kernel);
    liberateMemory( &kernel);
    return(dest);
}
