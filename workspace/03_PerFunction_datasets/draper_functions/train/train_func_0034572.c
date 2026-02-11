sendFrame(u_char fcf, FaxParams& dcs_caps, bool lastFrame)
{
    HDLCFrame frame(conf.class1FrameOverhead);
    frame.put(0xff);
    frame.put(lastFrame ? 0xc8 : 0xc0);
    frame.put(fcf);

    int curByte = 0;

    frame.put(dcs_caps.getByte(curByte));
    while (dcs_caps.hasNextByte(curByte)) {
        curByte += 1;
        frame.put(dcs_caps.getByte(curByte));
    }

    return (sendRawFrame(frame));
}
