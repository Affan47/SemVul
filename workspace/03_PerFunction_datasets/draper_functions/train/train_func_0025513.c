generateNoise(unsigned int pixel,
                                         NoiseType noise_type)
{
#define NoiseEpsilon  1.0e-5
#define NoiseMask  0x7fff
#define SigmaUniform  4.0
#define SigmaGaussian  4.0
#define SigmaImpulse  0.10
#define SigmaLaplacian 10.0
#define SigmaMultiplicativeGaussian  0.5
#define SigmaPoisson  0.05
#define TauGaussian  20.0

    double alpha, beta, sigma, value;
    alpha=(double) (rand() & NoiseMask)/NoiseMask;
    if (alpha == 0.0)
        alpha=1.0;
    switch(noise_type){
    case UniformNoise:
    default:
        {
            value=(double) pixel+SigmaUniform*(alpha-0.5);
            break;
        }
    case GaussianNoise:
        {
            double tau;

            beta=(double) (rand() & NoiseMask)/NoiseMask;
            sigma=sqrt(-2.0*log(alpha))*cos(2.0*M_PI*beta);
            tau=sqrt(-2.0*log(alpha))*sin(2.0*M_PI*beta);
            value=(double) pixel+
                (sqrt((double) pixel)*SigmaGaussian*sigma)+(TauGaussian*tau);
            break;
        }
    case MultiplicativeGaussianNoise:
        {
            if (alpha <= NoiseEpsilon)
                sigma=MaxRGB;
            else
                sigma=sqrt(-2.0*log(alpha));
            beta=(rand() & NoiseMask)/NoiseMask;
            value=(double) pixel+
                pixel*SigmaMultiplicativeGaussian*sigma*cos(2.0*M_PI*beta);
            break;
        }
    case ImpulseNoise:
        {
            if (alpha < (SigmaImpulse/2.0))
                value=0;
            else
                if (alpha >= (1.0-(SigmaImpulse/2.0)))
                    value=MaxRGB;
                else
                    value=pixel;
            break;
        }
    case LaplacianNoise:
        {
            if (alpha <= 0.5)
            {
                if (alpha <= NoiseEpsilon)
                    value=(double) pixel-MaxRGB;
                else
                    value=(double) pixel+SigmaLaplacian*log(2.0*alpha);
                break;
            }
            beta=1.0-alpha;
            if (beta <= (0.5*NoiseEpsilon))
                value=(double) pixel+MaxRGB;
            else
                value=(double) pixel-SigmaLaplacian*log(2.0*beta);
            break;
        }
    case PoissonNoise:
        {
            register int
                i;

            for (i=0; alpha > exp(-SigmaPoisson*pixel); i++)
            {
                beta=(double) (rand() & NoiseMask)/NoiseMask;
                alpha=alpha*beta;
            }
            value=i/SigmaPoisson;
            break;
        }
    }
    if(value < 0.0)
        return(0);
    if(value > MaxRGB)
        return(MaxRGB);
    return((unsigned int) (value+0.5));
}
