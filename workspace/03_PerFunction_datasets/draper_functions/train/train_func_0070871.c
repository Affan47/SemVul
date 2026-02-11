img_resample(ImgReSampleContext *s,
                  AVPicture *output, const AVPicture *input)
{
    int i, shift;
    uint8_t* optr;

    for (i=0;i<3;i++) {
        shift = (i == 0) ? 0 : 1;

        optr = output->data[i] + (((output->linesize[i] *
                        s->padtop) + s->padleft) >> shift);

        component_resample(s, optr, output->linesize[i],
                s->pad_owidth >> shift, s->pad_oheight >> shift,
                input->data[i] + (input->linesize[i] *
                    (s->topBand >> shift)) + (s->leftBand >> shift),
                input->linesize[i], ((s->iwidth - s->leftBand -
                        s->rightBand) >> shift),
                           (s->iheight - s->topBand - s->bottomBand) >> shift);
    }
}
