Protocol_CAPABILITY(PROTO_PARMS) {
    KisNetFramework::server_protocol *proto =
        (KisNetFramework::server_protocol *) data;

    out_string = proto->header + " ";

    for (unsigned int x = 0; x < proto->field_vec.size(); x++) {
        out_string += proto->field_vec[x] + ",";
    }

    out_string = out_string.substr(0, out_string.length() - 1);

    return 1;
}
