skipElementValue(u1 *data_ptr, int *data_len) {
    char tag;

    READ_U1(tag, data_ptr, *data_len);

    switch(tag) {
        case 'e':
            SKIP_U2(idx, data_ptr, *data_len);


        case 'Z': case 'B': case 'C': case 'S': case 'I':
        case 'F': case 'J': case 'D': case 's': case 'c':
            SKIP_U2(idx, data_ptr, *data_len);
            break;

        case '@':
            data_ptr = skipAnnotation(data_ptr, data_len);
            break;

        case '[': {
            int i, num_values;

            READ_U2(num_values, data_ptr, *data_len);

            for(i = 0; i < num_values; i++)
                data_ptr = skipElementValue(data_ptr, data_len);

            break;
        }
    }

    return data_ptr;
}
