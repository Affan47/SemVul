getOverlayDescriptor(int bitDepthPerComponent, bool hasAlpha)
      {
        if(_overlayDescriptor.getState() == Interact::eUninitialised) {

          _overlayDescriptor.setEntryPoint(getOverlayInteractMainEntry());
          _overlayDescriptor.describe(bitDepthPerComponent, hasAlpha);
        }

        return _overlayDescriptor;
      }
