render()
    {

        const WidgetLookFeel& wlf = getLookNFeel();

        wlf.getStateImagery(d_window->isDisabled() ? "Disabled" : "Enabled").render(*d_window);
    }

}
