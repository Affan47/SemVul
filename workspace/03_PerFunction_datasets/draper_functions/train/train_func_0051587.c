Scale(const char *request) {
    int bbox=FindBbox(request);
    if (bbox<0) return 0;
    double x,y,X,Y;
    sscanf(request+bbox,"%lf,%lf,%lf,%lf",&x,&y,&X,&Y);
    return (m_data_window.m_x1-m_data_window.m_x0)/(X-x)*m_bsx/m_data_window.m_sx;
}
