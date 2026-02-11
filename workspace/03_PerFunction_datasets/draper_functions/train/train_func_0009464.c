dCollideCapsuleSphere (dxGeom *o1, dxGeom *o2, int flags,
			     dContactGeom *contact, int skip)
{
  dIASSERT (skip >= (int)sizeof(dContactGeom));
  dIASSERT (o1->type == dCapsuleClass);
  dIASSERT (o2->type == dSphereClass);
  dIASSERT ((flags & NUMC_MASK) >= 1);

  dxCapsule *ccyl = (dxCapsule*) o1;
  dxSphere *sphere = (dxSphere*) o2;

  contact->g1 = o1;
  contact->g2 = o2;
  contact->side1 = -1;
  contact->side2 = -1;


  dReal alpha =
    o1->final_posr->R[2]  * (o2->final_posr->pos[0] - o1->final_posr->pos[0]) +
    o1->final_posr->R[6]  * (o2->final_posr->pos[1] - o1->final_posr->pos[1]) +
    o1->final_posr->R[10] * (o2->final_posr->pos[2] - o1->final_posr->pos[2]);
  dReal lz2 = ccyl->lz * REAL(0.5);
  if (alpha > lz2) alpha = lz2;
  if (alpha < -lz2) alpha = -lz2;


  dVector3 p;
  p[0] = o1->final_posr->pos[0] + alpha * o1->final_posr->R[2];
  p[1] = o1->final_posr->pos[1] + alpha * o1->final_posr->R[6];
  p[2] = o1->final_posr->pos[2] + alpha * o1->final_posr->R[10];
  return dCollideSpheres (p,ccyl->radius,o2->final_posr->pos,sphere->radius,contact);
}
