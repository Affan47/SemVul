getSpinScan(double spinData[])
{
    pvars.lock();
    for (int i=0; i<24; spinData[i] = this->spinScan[i]) ;
    pvars.unlock();
}
