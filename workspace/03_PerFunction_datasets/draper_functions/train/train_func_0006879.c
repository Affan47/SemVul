ml600_print_page(
        gx_device_printer	*pdev,
        FILE	*prn_stream)
{
        int	ystep;
        byte	data[2][LINE_SIZE*2];
        byte	buf[LINE_SIZE*2];
        int	skip;
        int	current;
        int	c_size;
        int	lnum;
        int	line_size;
        byte	rmask;
        int	i;

#define LAST	((current ^ 1) & 1)


        ystep = page_header(pdev, prn_stream);
        ystep /= 300;


        skip = 0;
        current = 0;
        for (i = 0; i < LINE_SIZE*2; i++)
                data[LAST][i] = 0;


        line_size = gdev_mem_bytes_per_scan_line((gx_device *)pdev);
        if (line_size > LINE_SIZE || line_size == 0)
                return 0;

        rmask = (byte)(0xff << (-pdev->width & 7));

        for (lnum = 0; lnum < pdev->height; lnum++) {
                int	s;

                s = gdev_prn_copy_scan_lines(pdev, lnum, data[current],
                                                                line_size);

                *(data[current] + line_size - 1) &= rmask;


                for (i = 0; i < line_size; i++)
                        if (data[current][i] != 0)
                                break;

                if (i == line_size) {
                        skip = 1;
                        current = LAST;
                        continue;
                }


                if (skip) {
                        move_pos(prn_stream, lnum / ystep, lnum % ystep);
                        skip = 0;
                }


                c_size = make_line_data(data[current], data[LAST],
                                                                line_size, buf);


                send_line(buf, c_size, prn_stream);


                current = LAST;
        }


        fprintf(prn_stream, "\014");

        return 0;
}
