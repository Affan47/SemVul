dc1394_pxl_get_gpio_inq(dc1394camera_t *camera, dc1394_pxl_gpio_info_t *gpio_info)
{
    uint32_t gpio_inq;

    if (camera == NULL)
        return DC1394_FAILURE;

    uint32_t address = PxL_ACR_GPIO_INQ;
    dc1394_get_adv_control_register(camera, address, &gpio_inq);
#ifdef PIXELINK_DEBUG_DISPLAY
    printf("  0x%08x : r 0x%08x < GPIO_INQ\n", address, gpio_inq);
#endif

    uint32_t bit = 0x1UL << 31;
    gpio_info->number      = (gpio_inq>>24) & 0x0FUL;

    gpio_info->presence    = gpio_inq & (bit>> 0)? DC1394_TRUE: DC1394_FALSE;
    gpio_info->polarity    = gpio_inq & (bit>> 1)? DC1394_TRUE: DC1394_FALSE;
    gpio_info->mode_strobe = gpio_inq & (bit>> 8)? DC1394_TRUE: DC1394_FALSE;
    gpio_info->mode_normal = gpio_inq & (bit>> 9)? DC1394_TRUE: DC1394_FALSE;
    gpio_info->mode_pulse  = gpio_inq & (bit>>10)? DC1394_TRUE: DC1394_FALSE;
    gpio_info->mode_busy   = gpio_inq & (bit>>11)? DC1394_TRUE: DC1394_FALSE;
    gpio_info->mode_flash  = gpio_inq & (bit>>12)? DC1394_TRUE: DC1394_FALSE;

    if (gpio_info->presence == DC1394_FALSE) {
        gpio_info->number      = 0;
        gpio_info->polarity    = DC1394_FALSE;
        gpio_info->mode_strobe = DC1394_FALSE;
        gpio_info->mode_normal = DC1394_FALSE;
        gpio_info->mode_pulse  = DC1394_FALSE;
        gpio_info->mode_busy   = DC1394_FALSE;
        gpio_info->mode_flash  = DC1394_FALSE;
    }

#ifdef PIXELINK_DEBUG_LOWEST_LEVEL
    printf("\n");
    printf("  Presence ---------------------------------+\n");
    printf("  Polarity inq ----------------------------+|\n");
    printf("  Number of supported GPIOs ---------+--+  ||\n");
    printf("  Strobe mode ----------------------+|  |  ||\n");
    printf("  Normal mode ---------------------+||  |  ||\n");
    printf("  Pulse mode ---------------------+|||  |  ||\n");
    printf("  Busy mode ---------------------+||||  |  ||\n");
    printf("                                 |||||  |  ||\n");
    printf("  GPIO_INQ : ");

    uint32_t i;
    for (i = 0; i < 32; i++) {
        (gpio_inq & (1<<i))? printf("1"): printf("0");
    }
    printf("\n\n");
#endif

    return DC1394_SUCCESS;
}
