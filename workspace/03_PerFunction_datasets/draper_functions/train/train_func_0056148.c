TcpDataEntry(int sock)
{
        TcpData tdata;

        tdata.sock = sock;
        tdata.DispatchTcpData();
}
