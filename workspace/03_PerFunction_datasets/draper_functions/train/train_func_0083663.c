readBit(bool value) {
    if(verbose)
      cout << name() << " " << __FUNCTION__ << " got readbit = " << value << endl;
    if (value)
        octetBuffer[bitRemaining / 8] |= 1 << (7 - bitRemaining % 8);
    else
        octetBuffer[bitRemaining / 8] &= ~(1 << (7 - bitRemaining % 8));

    if (verbose && (bitRemaining % 8) == 0)
    {
	printf("%s read byte %0x index %d\n", name().c_str(), octetBuffer[bitRemaining / 8], (bitRemaining / 8));
    }
}
