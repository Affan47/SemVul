reset(_u32 timeout)
{
    u_result ans;
    if (IS_FAIL(ans = _sendCommand(RPLIDAR_CMD_RESET))) {
        return ans;
    }
    return RESULT_OK;
}
