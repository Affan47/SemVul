decode_plane(FFV1Context *s, uint8_t *src, int w, int h, int stride, int plane_index){
    int x, y;
    int_fast16_t sample_buffer[2][w+6];
    int_fast16_t *sample[2];
    sample[0]=sample_buffer[0]+3;
    sample[1]=sample_buffer[1]+3;

    s->run_index=0;

    memset(sample_buffer, 0, sizeof(sample_buffer));

    for(y=0; y<h; y++){
        int_fast16_t *temp= sample[0];

        sample[0]= sample[1];
        sample[1]= temp;

        sample[1][-1]= sample[0][0  ];
        sample[0][ w]= sample[0][w-1];


        decode_line(s, w, sample, plane_index, 8);
        for(x=0; x<w; x++){
            src[x + stride*y]= sample[1][x];
        }

    }
}
