z_jin (void)
{
    zword obj_addr;


    if (f_setup.object_locating) {
	stream_mssg_on ();
	print_string ("@jin ");
	print_object (zargs[0]);
	print_string (" ");
	print_object (zargs[1]);
	stream_mssg_off ();
    }

    if (zargs[0] == 0) {
	runtime_error (ERR_JIN_0);
	branch (0 == zargs[1]);
	return;
    }

    obj_addr = object_address (zargs[0]);

    if (h_version <= V3) {

	zbyte parent;


	obj_addr += O1_PARENT;
	LOW_BYTE (obj_addr, parent)


	branch (parent == zargs[1]);

    } else {

	zword parent;


	obj_addr += O4_PARENT;
	LOW_WORD (obj_addr, parent)


	branch (parent == zargs[1]);

    }

}
