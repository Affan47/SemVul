adpcm_yamaha_compress_sample(ADPCMChannelStatus *c, short sample)
{
    int nibble, delta;

    if(!c->step) {
        c->predictor = 0;
        c->step = 127;
    }

    delta = sample - c->predictor;

    nibble = FFMIN(7, abs(delta)*4/c->step) + (delta<0)*8;

    c->predictor += ((c->step * yamaha_difflookup[nibble]) / 8);
    c->predictor = av_clip_int16(c->predictor);
    c->step = (c->step * yamaha_indexscale[nibble]) >> 8;
    c->step = av_clip(c->step, 127, 24567);

    return nibble;
}
