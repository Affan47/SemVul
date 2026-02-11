getDoublePropertyN(const std::string &name, double* first, int n) const OFX_EXCEPTION_SPEC
      {
        if(name==kOfxImageEffectPropProjectSize){
          if(n>2) throw Property::Exception(kOfxStatErrBadIndex);
          getProjectSize(first[0],first[1]);
        }
        else if(name==kOfxImageEffectPropProjectOffset){
          if(n>2) throw Property::Exception(kOfxStatErrBadIndex);
          getProjectOffset(first[0],first[1]);
        }
        else if(name==kOfxImageEffectPropProjectExtent){
          if(n>2) throw Property::Exception(kOfxStatErrBadIndex);
          getProjectExtent(first[0],first[1]);
        }
        else if(name==kOfxImageEffectPropProjectPixelAspectRatio){
          if(n>1) throw Property::Exception(kOfxStatErrBadIndex);
          *first = getProjectPixelAspectRatio();
        }
        else if(name==kOfxImageEffectInstancePropEffectDuration){
          if(n>1) throw Property::Exception(kOfxStatErrBadIndex);
          *first = getEffectDuration();
        }
        else if(name==kOfxImageEffectPropFrameRate){
          if(n>1) throw Property::Exception(kOfxStatErrBadIndex);
          *first = getFrameRate();
        }
        else
          throw Property::Exception(kOfxStatErrUnknown);
      }
