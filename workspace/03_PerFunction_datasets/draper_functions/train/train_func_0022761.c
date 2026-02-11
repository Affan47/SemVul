dt282x_timer(double freq,unsigned int *trigvar,double *actual_freq)
{
	int divider,prescaler;
	double basefreq=4e6;

	divider=floor(4e6/(freq));
	prescaler=0;
	while(divider>255){
		prescaler++;
		divider>>=1;
		basefreq/=2;
	}
	if(prescaler==1){
		prescaler++;
		divider>>=1;
		basefreq/=2;
	}
	if(prescaler>=16)return -1;
	*trigvar=(prescaler<<8)|(255-divider);
	*actual_freq=basefreq/divider;

	return 0;
}
