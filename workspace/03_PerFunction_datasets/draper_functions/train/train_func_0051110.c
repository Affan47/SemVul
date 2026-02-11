DestroyServer()
{
    for (int i = 0; i < tcpServer_.max_conn_id; ++i)
    {
        if (conn_[i]) delete conn_[i];
    }

    delete[] conn_;
}
