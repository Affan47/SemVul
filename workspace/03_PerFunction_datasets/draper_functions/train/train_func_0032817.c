read_detail_page()
    {
        int sum = 0;
        int bytes_read = 0;

        char header1 = read_bytes(1, &bytes_read, &sum);
        char header2 = read_bytes(1, &bytes_read, &sum);
        uint16_t command = read_bytes(2, &bytes_read, &sum);

        if (header1 == 0x10 && header2 == 0x02 && command == 0x2022)
        {
            read_bytes(2, &bytes_read, &sum);
            uint16_t page_number = read_bytes(2, &bytes_read, &sum);

            if (page_number > 0) {


                QDateTime t;


                for (int i = 0; i < 128; i++) {
                    int flag = read_bytes(1, &bytes_read, &sum);


                    if (flag == 0xff) {

                        read_bytes(31, &bytes_read, &sum);
                    }
                    else if ((flag & 0x03) == 0x01){
                        t= read_RTC_mark(&secs, &bytes_read, &sum);
                    }
                    else if ((flag & 0x03) == 0x03){
                        int t = read_interval_mark(&secs, &bytes_read, &sum);
                        interval = t;
                    }
                    else if ((flag & 0x03) == 0x00 ){
                        read_detail_record(&secs, &bytes_read, &sum);
                    }

                }
                read_bytes(1, &bytes_read, &sum);

            }


        }

        return bytes_read;
    }
