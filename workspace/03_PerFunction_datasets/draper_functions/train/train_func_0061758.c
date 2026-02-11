noteon(n)

int n;
{
  int i, vel;


  if(beataccents == 0)
    vel = mednote;
  else if (nbeats > 0) {
      if ((bar_num*nbeats)%(bar_denom*barsize) != 0) {

        vel = softnote;
      } else {

        i = ((bar_num*nbeats)/(bar_denom*barsize))%nbeats;
        switch(beatstring[i]) {
        case 'f':
        case 'F':
          vel = loudnote;
          break;
        case 'm':
        case 'M':
          vel = mednote;
          break;
        default:
        case 'p':
        case 'P':
          vel = softnote;
          break;
        };
      };
     } else {

      if (bar_num == 0) {
          vel = loudnote;
     } else {
        if ((bar_denom == 1) && ((bar_num % beat) == 0)) {
          vel = mednote;
     } else {
          vel = softnote;
        };
      };
    }
  if (channel == 9) noteon_data(pitch[n],bentpitch[n],channel,vel);
  else noteon_data(pitch[n] + transpose + global_transpose, bentpitch[n], channel, vel);
}
