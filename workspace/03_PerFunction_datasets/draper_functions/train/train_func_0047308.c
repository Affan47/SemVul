v_fs_unpack(uint8 *data, unsigned int length)
{
	uint32 i, output, pack_id;
	uint8 cmd_id, last = 255;

	i = vnp_raw_unpack_uint32(data, &pack_id);
	vnp_raw_unpack_uint8(&data[i], &cmd_id);
	while(i < length && (cmd_id == 7 || cmd_id == 8))
	{
		i += 5;
		vnp_raw_unpack_uint8(&data[i], &cmd_id);
	}
	while(i < length)
	{
		i += vnp_raw_unpack_uint8(&data[i], &cmd_id);
		if(VCmdData.unpack_func[cmd_id] != NULL)
		{
			VCmdData.call = TRUE;
			output = VCmdData.unpack_func[cmd_id](&data[i], length - i);
			if(output == (unsigned int) -1)
			{
				printf("** Aborting decode, command %u unpacker returned failure\n", cmd_id);

				return;
			}
			last = cmd_id;
			i += output;
		}
		else
		{
			size_t	j;

			printf("\n** Unknown command ID %u (0x%02X) encountered--aborting packet decode len=%u pos=%u last=%u\n", cmd_id, cmd_id, length, i, last);
			printf(" decoded %u bytes: ", --i);
			for(j = 0; j < i; j++)
				printf("%02X ", data[j]);
			printf("\n (packet id=%u)", pack_id);
			printf(" remaining %u bytes: ", length - i);
			for(j = i; j < length; j++)
				printf("%02X ", data[j]);
			printf("\n");

			break;
		}
	}


}
