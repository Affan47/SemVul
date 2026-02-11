onConnected(Eris::Connection * c)
{
    std::cout << "connected to server" << std::endl;
    if (--connection_count == 0) {
        done = true;
    }
}
