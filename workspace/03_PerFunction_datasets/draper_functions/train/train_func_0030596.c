e1000_set_media_type(struct e1000_hw *hw)
{
    uint32_t status;

    DEBUGFUNC("e1000_set_media_type");

    if (hw->mac_type != e1000_82543) {

        hw->tbi_compatibility_en = FALSE;
    }

    switch (hw->device_id) {
    case E1000_DEV_ID_82545GM_SERDES:
    case E1000_DEV_ID_82546GB_SERDES:
    case E1000_DEV_ID_82571EB_SERDES:
    case E1000_DEV_ID_82571EB_SERDES_DUAL:
    case E1000_DEV_ID_82571EB_SERDES_QUAD:
    case E1000_DEV_ID_82572EI_SERDES:
    case E1000_DEV_ID_80003ES2LAN_SERDES_DPT:
        hw->media_type = e1000_media_type_internal_serdes;
        break;
    default:
        switch (hw->mac_type) {
        case e1000_82542_rev2_0:
        case e1000_82542_rev2_1:
            hw->media_type = e1000_media_type_fiber;
            break;
        case e1000_ich8lan:
        case e1000_82573:
        case e1000_82576:


            hw->media_type = e1000_media_type_copper;
            break;
        default:
            status = E1000_READ_REG(hw, STATUS);
            if (status & E1000_STATUS_TBIMODE) {
                hw->media_type = e1000_media_type_fiber;

                hw->tbi_compatibility_en = FALSE;
            } else {
                hw->media_type = e1000_media_type_copper;
            }
            break;
        }
    }
}
