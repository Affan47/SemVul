printInteger(STD_NAMESPACE ostream& stream) const
{


    char buffer[40];

    Uint32 data[4];
    struct BinaryRepresentation representation;


    int idx = sizeof(buffer) - 1;


    getBinaryRepresentation(representation);
    for (int i = 0; i < 4; i++) {
        data[i]  = representation.value[0 + 4*i] << 24;
        data[i] |= representation.value[1 + 4*i] << 16;
        data[i] |= representation.value[2 + 4*i] <<  8;
        data[i] |= representation.value[3 + 4*i] <<  0;
    }

    if (data[0] == 0 && data[1] == 0 && data[2] == 0 && data[3] == 0) {

        stream << "0";
        return;
    }


    while (data[0] != 0 || data[1] != 0 || data[2] != 0 || data[3] != 0) {
        Uint32 rem = 0;
        divide_by(data[0], 10, data[0], rem);
        divide_by(data[1], 10, data[1], rem);
        divide_by(data[2], 10, data[2], rem);
        divide_by(data[3], 10, data[3], rem);

        assert(rem <= 9);
        buffer[--idx] = OFstatic_cast(char, rem + '0');
    }
    assert(idx >= 0);
    buffer[sizeof(buffer) - 1] = '\0';
    stream << &buffer[idx];
}
