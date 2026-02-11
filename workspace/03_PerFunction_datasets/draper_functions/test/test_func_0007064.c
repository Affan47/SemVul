Process ( MIDITimedBigMessage *msg )
{

    if ( mute )
    {

        return false;
    }


    if ( msg->IsNoOp() )
    {

        return false;
    }


    if ( extra_proc && extra_proc->Process ( msg ) == false )
    {

        return false;
    }


    if ( msg->IsChannelMsg() )
    {

        if ( rechannel != -1 )
        {
            msg->SetChannel ( ( unsigned char ) rechannel );
        }


        if ( msg->IsNoteOn() && msg->GetVelocity() != 0 )
        {

            int vel = ( int ) msg->GetVelocity();
            vel = vel * velocity_scale / 100;


            if ( vel < 0 )
            {
                vel = 0;
            }


            msg->SetVelocity ( ( unsigned char ) vel );
        }


        if ( msg->IsNoteOn() || msg->IsNoteOff() || msg->IsPolyPressure() )
        {
            int new_note = ( ( int ) msg->GetNote() ) + transpose;

            if ( new_note >= 0 && new_note <= 127 )
            {

                msg->SetNote ( ( unsigned char ) new_note );
            }

            else
            {

                return false;
            }
        }
    }

    return true;
}
