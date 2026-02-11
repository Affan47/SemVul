viewMessCallback(void *data, t_symbol *, int argc, t_atom *argv)
{
  const float DEG2RAD = 0.01745329251994f;
  float azimuth = 0.f;
  float theta = 0.f;
  float distance = 1.f;

  if (GemMan::m_stereoFocal > 0)
    {
      distance = GemMan::m_stereoFocal;
    }

  switch (argc)
    {

    case 9 :
      GemMan::m_lookat[0] = atom_getfloat(&argv[0]);
      GemMan::m_lookat[1] = atom_getfloat(&argv[1]);
      GemMan::m_lookat[2] = atom_getfloat(&argv[2]);
      GemMan::m_lookat[3] = atom_getfloat(&argv[3]);
      GemMan::m_lookat[4] = atom_getfloat(&argv[4]);
      GemMan::m_lookat[5] = atom_getfloat(&argv[5]);
      GemMan::m_lookat[6] = atom_getfloat(&argv[6]);
      GemMan::m_lookat[7] = atom_getfloat(&argv[7]);
      GemMan::m_lookat[8] = atom_getfloat(&argv[8]);
      break;

    case 5 :
      theta	= static_cast<float>(DEG2RAD) * atom_getfloat(&argv[4]);

    case 4 :
      azimuth = static_cast<float>(DEG2RAD) * atom_getfloat(&argv[3]);


    case 3 :
      {
	const float dx =  static_cast<float>(cos(theta) * sinf(azimuth));
	const float dy =  static_cast<float>(sin(theta));
	const float dz = -static_cast<float>(cos(theta) * cosf(azimuth));

	GemMan::m_lookat[0] = atom_getfloat(&argv[0]);
	GemMan::m_lookat[1] = atom_getfloat(&argv[1]);
	GemMan::m_lookat[2] = atom_getfloat(&argv[2]);
	GemMan::m_lookat[3] = GemMan::m_lookat[0] + dx * distance;
	GemMan::m_lookat[4] = GemMan::m_lookat[1] + dy * distance;
	GemMan::m_lookat[5] = GemMan::m_lookat[2] + dz * distance;
	GemMan::m_lookat[6] = -dx*dy;
	GemMan::m_lookat[7] = dx*dx+dz*dz;
	GemMan::m_lookat[8] = -dy*dz;
      }
      break;

    default:
      GetMyClass(data)->error("view message needs 3, 4, 5 or 9 arguments");


    }
}
