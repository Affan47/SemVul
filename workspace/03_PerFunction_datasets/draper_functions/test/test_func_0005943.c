dump_daq_set_errbuf (void* handle, const char* s)
{
    DumpImpl* impl = (DumpImpl*)handle;
    impl->module->set_errbuf(impl->handle, s ? s : "");
}
