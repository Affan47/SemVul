resume(YieldingIOStrategy *io)
{
    YieldingIOStrategy::Need n = (YieldingIOStrategy::Need)io->resume();
    switch(n) {
        case YieldingIOStrategy::READ:
            register_connection(io, EV_READ);
            break;

        case YieldingIOStrategy::WRITE:
            register_connection(io, EV_WRITE);
            break;

        case YieldingIOStrategy::HALT:
            delete io;
            break;
    }
}
