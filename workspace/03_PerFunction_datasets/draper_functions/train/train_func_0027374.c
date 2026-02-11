svq1_write_header(SVQ1Context *s, int frame_type)
{
    int i;


    put_bits(&s->pb, 22, 0x20);


    put_bits(&s->pb, 8, 0x00);


    put_bits(&s->pb, 2, frame_type - 1);

    if (frame_type == FF_I_TYPE) {


        put_bits(&s->pb, 5, 2);

        for (i = 0; i < 7; i++)
        {
            if ((ff_svq1_frame_size_table[i].width == s->frame_width) &&
                (ff_svq1_frame_size_table[i].height == s->frame_height))
            {
                put_bits(&s->pb, 3, i);
                break;
            }
        }

        if (i == 7)
        {
            put_bits(&s->pb, 3, 7);
                put_bits(&s->pb, 12, s->frame_width);
                put_bits(&s->pb, 12, s->frame_height);
        }
    }


    put_bits(&s->pb, 2, 0);
}
