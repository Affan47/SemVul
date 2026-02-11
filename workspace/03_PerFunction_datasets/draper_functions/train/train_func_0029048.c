send_crafted_request(modbus_t *ctx, int function,
                         uint8_t *req, int req_len,
                         uint16_t max_value, uint16_t bytes,
                         int backend_length, int backend_offset)
{
    const int EXCEPTION_RC = 2;
    uint8_t rsp[MODBUS_TCP_MAX_ADU_LENGTH];
    int j;
    uint32_t old_response_to_sec;
    uint32_t old_response_to_usec;


    modbus_get_response_timeout(ctx, &old_response_to_sec, &old_response_to_usec);
    modbus_set_response_timeout(ctx, 0, 600000);

    for (j=0; j<2; j++) {
        int rc;

        req[1] = function;
        if (j == 0) {

            req[4] = 0x00;
            req[5] = 0x00;
            if (bytes) {

                req[6] = 0x00;
            }
        } else {

            req[4] = (max_value >> 8) & 0xFF;
            req[5] = max_value & 0xFF;
            if (bytes) {

                req[6] = bytes;
            }
        }

        modbus_send_raw_request(ctx, req, req_len * sizeof(uint8_t));
        if (j == 0) {
            printf("* try function 0x%X: %s 0 values: ", function, bytes ? "write": "read");
        } else {
            printf("* try function 0x%X: %s %d values: ", function, bytes ? "write": "read",
                   max_value);
        }
        rc = modbus_receive_confirmation(ctx, rsp);
        ASSERT_TRUE(rc == (backend_length + EXCEPTION_RC) &&
                    rsp[backend_offset] == (0x80 + function) &&
                    rsp[backend_offset + 1] == MODBUS_EXCEPTION_ILLEGAL_DATA_VALUE, "");
    }
    modbus_set_response_timeout(ctx, old_response_to_sec, old_response_to_usec);
    return 0;
close:
    modbus_set_response_timeout(ctx, old_response_to_sec, old_response_to_usec);
    return -1;
}
