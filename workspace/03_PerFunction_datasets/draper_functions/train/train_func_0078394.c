compute()
{
    if (ride == NULL) {
        return;
    }


    MeanMaxComputer thread1(ride, wattsMeanMax, RideFile::watts); thread1.start();
    MeanMaxComputer thread2(ride, hrMeanMax, RideFile::hr); thread2.start();
    MeanMaxComputer thread3(ride, cadMeanMax, RideFile::cad); thread3.start();
    MeanMaxComputer thread4(ride, nmMeanMax, RideFile::nm); thread4.start();
    MeanMaxComputer thread5(ride, kphMeanMax, RideFile::kph); thread5.start();
    MeanMaxComputer thread6(ride, xPowerMeanMax, RideFile::xPower); thread6.start();
    MeanMaxComputer thread7(ride, npMeanMax, RideFile::NP); thread7.start();
    MeanMaxComputer thread8(ride, vamMeanMax, RideFile::vam); thread8.start();
    MeanMaxComputer thread9(ride, wattsKgMeanMax, RideFile::wattsKg); thread9.start();


    computeDistribution(wattsDistribution, RideFile::watts);
    computeDistribution(hrDistribution, RideFile::hr);
    computeDistribution(cadDistribution, RideFile::cad);
    computeDistribution(nmDistribution, RideFile::nm);
    computeDistribution(kphDistribution, RideFile::kph);
    computeDistribution(wattsKgDistribution, RideFile::wattsKg);


    thread1.wait();
    thread2.wait();
    thread3.wait();
    thread4.wait();
    thread5.wait();
    thread6.wait();
    thread7.wait();
    thread8.wait();
    thread9.wait();
}
