include(const FXSphered& sphere){
  register FXdouble dx,dy,dz,dist,delta,newradius;
  if(0.0<=sphere.radius){
    if(0.0<=radius){
      dx=sphere.center.x-center.x;
      dy=sphere.center.y-center.y;
      dz=sphere.center.z-center.z;
      dist=sqrt(dx*dx+dy*dy+dz*dz);
      if(sphere.radius<dist+radius){
        if(radius<dist+sphere.radius){
          newradius=0.5*(radius+dist+sphere.radius);
          delta=(newradius-radius);
          center.x+=delta*dx/dist;
          center.y+=delta*dy/dist;
          center.z+=delta*dz/dist;
          radius=newradius;
          }
        return *this;
        }
      }
    center=sphere.center;
    radius=sphere.radius;
    }
  return *this;
  }
