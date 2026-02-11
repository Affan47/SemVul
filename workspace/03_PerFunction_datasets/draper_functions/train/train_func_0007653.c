_vmCplFrameExport(const cpl_frame *self)
{

    PilFrame *frame = NULL;

    if (self != NULL) {

        const char *name = cpl_frame_get_filename(self);
        const char *tag = cpl_frame_get_tag(self);

        cpl_frame_group group = cpl_frame_get_group(self);


        if (name != NULL && tag != NULL) {

            frame = newPilFrame(name, tag);

            switch (group) {
                case CPL_FRAME_GROUP_NONE:
                    pilFrmSetType(frame, PIL_FRAME_TYPE_UNDEF);
                    break;

                case CPL_FRAME_GROUP_RAW:
                    pilFrmSetType(frame, PIL_FRAME_TYPE_RAW);
                    break;

                case CPL_FRAME_GROUP_CALIB:
                    pilFrmSetType(frame, PIL_FRAME_TYPE_CALIB);
                    break;

                case CPL_FRAME_GROUP_PRODUCT:
                    pilFrmSetType(frame, PIL_FRAME_TYPE_PRODUCT);
                    break;

                default:
                    deletePilFrame(frame);
                    return NULL;
                    break;
            }

        }

    }

    return frame;

}
