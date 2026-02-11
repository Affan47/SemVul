record(int command, const query_times& qtimes, Str key,
                     const lcdf::Json* req, const lcdf::Json* end_req) {
    lcdf::StringAccum sa(128);
    msgpack::unparser<lcdf::StringAccum> cu(sa);
    cu.write_array_header(end_req - req);
    for (; req != end_req; ++req)
        cu << *req;
    record(command, qtimes, key, Str(sa.data(), sa.length()));
}
