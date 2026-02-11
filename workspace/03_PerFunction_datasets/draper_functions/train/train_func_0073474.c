execute(const vector<string> &args, const map<string, string> &vars,
                            const boost::shared_ptr< GDBusCXX::Result1<bool> > &result)
{
    m_operation = boost::bind(&SessionHelper::doExecute, this, args, vars, result);
    g_main_loop_quit(m_loop);
}
