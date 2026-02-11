valueCallback(void *action,
    const SbVec3f &point,
    const SbVec3f &normal)


{
    SoAction *a = (SoAction *)action;


    const SbMatrix &mm = SoModelMatrixElement::get(a->getState());
    const SbMatrix &vm = SoViewingMatrixElement::get(a->getState());


    SbVec3f normalE;
    SbMatrix nm = (vm * mm).inverse().transpose();
    nm.multDirMatrix(normal, normalE);

    SbVec3f pointE;
    mm.multVecMatrix(point, pointE);
    vm.multVecMatrix(pointE, pointE);


    pointE.normalize();


    SbVec3f reflection = pointE - 2.0 * normalE.dot(normalE) * pointE;


    reflection[2] += 1.0;
    float magnitude = reflection.length();


    static SbVec4f result;
    result.setValue(reflection[0] / magnitude + 0.5,
		    reflection[1] / magnitude + 0.5,
		    0.0, 1.0);

    return result;
}
