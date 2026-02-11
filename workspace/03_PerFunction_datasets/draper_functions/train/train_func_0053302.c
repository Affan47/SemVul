preset(int nup,NupParameters &ret)
{
  switch (nup) {
  case 1:
    ret.nupX=1;
    ret.nupY=1;
    break;
  case 2:
    ret.nupX=2;
    ret.nupY=1;
    ret.landscape=true;
    break;
  case 3:
    ret.nupX=3;
    ret.nupY=1;
    ret.landscape=true;
    break;
  case 4:
    ret.nupX=2;
    ret.nupY=2;
    break;
  case 6:
    ret.nupX=3;
    ret.nupY=2;
    ret.landscape=true;
    break;
  case 8:
    ret.nupX=4;
    ret.nupY=2;
    ret.landscape=true;
    break;
  case 9:
    ret.nupX=3;
    ret.nupY=3;
    break;
  case 10:
    ret.nupX=5;
    ret.nupY=2;
    ret.landscape=true;
    break;
  case 12:
    ret.nupX=3;
    ret.nupY=4;
    break;
  case 15:
    ret.nupX=5;
    ret.nupY=3;
    ret.landscape=true;
    break;
  case 16:
    ret.nupX=4;
    ret.nupY=4;
    break;
  }
}
