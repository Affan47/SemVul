z_read (void)
{
    zchar buffer[INPUT_BUFFER_SIZE];
    zword addr;
    zchar key;
    zbyte max, size;
    zbyte c;
    int i;


    if (zargc < 3)
	zargs[2] = 0;


    addr = zargs[0];

    LOW_BYTE (addr, max)

    if (h_version <= V4)
	max--;

    if (max >= INPUT_BUFFER_SIZE)
	max = INPUT_BUFFER_SIZE - 1;


    if (h_version >= V5) {
	addr++;
	LOW_BYTE (addr, size)
    } else size = 0;


    for (i = 0; i < size; i++) {
	addr++;
	LOW_BYTE (addr, c)
	buffer[i] = translate_from_zscii (c);
    }

    buffer[i] = 0;


    if (h_version <= V3)
	z_show_status ();


    key = stream_read_input (
	max, buffer,
	zargs[2],
	zargs[3],
	TRUE,
	h_version == V6);

    if (key == ZC_BAD)
	return;


    if (h_version <= V4)
	save_undo ();


    for (i = 0; buffer[i] != 0; i++) {

	if (key == ZC_RETURN) {

	    if (buffer[i] >= 'A' && buffer[i] <= 'Z')
		buffer[i] += 'a' - 'A';
	    if (buffer[i] >= 0xc0 && buffer[i] <= 0xde && buffer[i] != 0xd7)
		buffer[i] += 0x20;

	}

	storeb ((zword) (zargs[0] + ((h_version <= V4) ? 1 : 2) + i), translate_to_zscii (buffer[i]));

    }


    if (h_version <= V4)
	storeb ((zword) (zargs[0] + 1 + i), 0);
    else
	storeb ((zword) (zargs[0] + 1), i);


    if (key == ZC_RETURN && zargs[1] != 0)
	tokenise_line (zargs[0], zargs[1], 0, FALSE);


    if (h_version >= V5)
	store (translate_to_zscii (key));

}
