setPin(u32 bank, u8 pin) {
    u32 pinMask = 0x1 << (pin);
    SET_REG(GPIO_BSRR(bank), pinMask);
}
