c6280_write(int which, int offset, int data)
{
    c6280_t *p = &c6280[which];
    t_channel *q = &p->channel[p->select];


    stream_update(stream[which], 0);

    switch(offset & 0x0F)
    {
        case 0x00:
            p->select = data & 0x07;
            break;

        case 0x01:
            p->balance  = data;
            break;

        case 0x02:
            q->frequency = (q->frequency & 0x0F00) | data;
            q->frequency &= 0x0FFF;
            break;

        case 0x03:
            q->frequency = (q->frequency & 0x00FF) | (data << 8);
            q->frequency &= 0x0FFF;
            break;

        case 0x04:


            if((q->control & 0x40) && ((data & 0x40) == 0))
            {
                q->index = 0;
            }
            q->control = data;
            break;

        case 0x05:
            q->balance = data;
            break;

        case 0x06:

            switch(q->control & 0xC0)
            {
                case 0x00:
                    q->waveform[q->index & 0x1F] = data & 0x1F;
                    q->index = (q->index + 1) & 0x1F;
                    break;

                case 0x40:
                    break;

                case 0x80:
                    q->waveform[q->index & 0x1F] = data & 0x1F;
                    q->index = (q->index + 1) & 0x1F;
                    break;

                case 0xC0:
                    q->dda = data & 0x1F;
                    break;
            }

            break;

        case 0x07:
            q->noise_control = data;
            break;

        case 0x08:
            p->lfo_frequency = data;
            break;

        case 0x09:
            p->lfo_control = data;
            break;

        default:
            break;
    }
}
