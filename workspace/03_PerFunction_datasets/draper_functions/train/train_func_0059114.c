getScreenPos(const Cube *model) const
{
    V2 shift(0, 0);
    Dir::eDir dir = model->getLastMoveDir();
    if (dir != Dir::DIR_NO) {
        shift = Dir::dir2xy(dir);
        shift = shift.scale(m_animShift);
    }
    shift = shift.plus(m_screenShift);

    V2 anim_shift = model->const_anim()->getViewShift();
    return model->getLocation().plus(anim_shift).scale(SCALE).plus(shift);
}
