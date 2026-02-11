OnRelease(cb_unused bool appShutDown)
{
    delete timer1;
    delete timer2;
    timer1 = 0;
    timer2 = 0;
}
