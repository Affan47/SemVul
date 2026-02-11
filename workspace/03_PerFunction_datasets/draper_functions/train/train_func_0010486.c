printRayCreator() {
    std::cout << "\nRayCreator:\n width = " << width << "\n height = " << height << "\nCamera Vector:\n";
    if(cam)
        camera->printVector();
    else
        std::cout << "\nNULL";
    if(viewPlane == NULL)
        std:cout << "\nViewPlane = NULL\n";
    std::cout << "\nViewPlane Normal:\n";
    if(planeN)
        viewPlane->normal->printVector();
    else
        std::cout << " NULL\n";
    std::cout << "\nViewPlane Center:\n";
    if(planeC)
        viewPlane->intersect->printVector();
    else
        std::cout << " NULL\n";

}
